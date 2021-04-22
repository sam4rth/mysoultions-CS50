import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    r = db.execute("SELECT * FROM stocks WHERE user_id = :user",user=session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = :user",user=session["user_id"])[0]['cash']

    total = cash
    stocks = []
    for index, row in enumerate(r):
        stock_info = lookup(row['symbol'])

        stocks.append(list((stock_info['symbol'], stock_info['name'], row['amount'], stock_info['price'], round(stock_info['price'] * row['amount'], 2))))
        total += stocks[index][4]

    return render_template("index.html", stocks=stocks, cash=round(cash, 2), total=round(total, 2))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        amount=int(request.form.get("amount"))
        symbol=lookup(request.form.get("symbol"))['symbol']

        if not lookup(symbol):
            return apology("Symbol not found!")

        price=lookup(symbol)['price']
        cash = db.execute("SELECT cash FROM users WHERE id = :user",user=session["user_id"])[0]['cash']
        cashleft = cash - price * float(amount)

        if cashleft < 0:
            return apology("You don't have enough cash!!!")

        stock = db.execute("SELECT amount FROM stocks WHERE user_id = :user AND symbol = :symbol",user=session["user_id"], symbol=symbol)

        if not stock:
            db.execute("INSERT INTO stocks(user_id, symbol, amount) VALUES (:user, :symbol, :amount)",user=session["user_id"], symbol=symbol, amount=amount)

        else:
            amount += stock[0]['amount']

            db.execute("UPDATE stocks SET amount = :amount WHERE user_id = :user AND symbol = :symbol",user=session["user_id"], symbol=symbol, amount=amount)

        db.execute("UPDATE users SET cash = :cash WHERE id = :user",cash=cashleft, user=session["user_id"])

        db.execute("INSERT INTO transactions(user_id, symbol, amount, value) VALUES (:user, :symbol, :amount, :value)",user=session["user_id"], symbol=symbol, amount=amount, value=round(price*float(amount)))

        flash("Order Completed!!!")

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    rows = db.execute("SELECT * FROM transactions WHERE user_id = :user",
                            user=session["user_id"])

    transactions = []
    for row in rows:
        stock_info = lookup(row['symbol'])

        transactions.append(list((stock_info['symbol'], stock_info['name'], row['amount'], row['value'], row['date'])))

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        data = lookup(request.form.get("symbol"))
        if not data:
            return apology("Symbol not found!", 404)
        return render_template("quoted.html",name=data["name"],symbol=data["symbol"],cost=data["price"])
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        # check if the input is valid
        if not request.form.get("username"):
            return apology("must provide username", 403)
        elif not request.form.get("password"):
            return apology("must provide password", 403)
        elif not request.form.get("cpassword"):
            return apology("must confirm provide password", 403)
        elif request.form.get("password") != request.form.get("cpassword"):
            return apology("Passwords do not match!!!", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username is not taken
        if len(rows) != 0:
            return apology("Sorry! Username is taken...", 403)

        #add the username and hashed password to data base
        db.execute("INSERT INTO users (username, hash) VALUES (:name, :hash1)", name=request.form.get("username"), hash1=generate_password_hash(request.form.get("password")))
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        amount=int(request.form.get("amount"))
        symbol=request.form.get("symbol")
        price=lookup(symbol)["price"]
        value=round(price*float(amount))

        before = db.execute("SELECT amount FROM stocks WHERE user_id = :user AND symbol = :symbol",
                          symbol=symbol, user=session["user_id"])[0]['amount']
        after = before - amount

        if after == 0:
            db.execute("DELETE FROM stocks WHERE user_id = :user AND symbol = :symbol",
                          symbol=symbol, user=session["user_id"])

        elif after < 0:
            return apology("That's more than the stocks you own")

        else:
            db.execute("UPDATE stocks SET amount = :amount WHERE user_id = :user AND symbol = :symbol",
                          symbol=symbol, user=session["user_id"], amount=after)

        cash = db.execute("SELECT cash FROM users WHERE id = :user",
                          user=session["user_id"])[0]['cash']
        cash_after = cash + price * float(amount)

        db.execute("UPDATE users SET cash = :cash WHERE id = :user",
                          cash=cash_after, user=session["user_id"])

        db.execute("INSERT INTO transactions(user_id, symbol, amount, value) VALUES (:user, :symbol, :amount, :value)",
                user=session["user_id"], symbol=symbol, amount=-amount, value=value)

        flash("Sold!")
        return redirect("/")

    else:

        rows = db.execute("SELECT symbol, amount FROM stocks WHERE user_id = :user",
                            user=session["user_id"])

        stocks = {}
        for row in rows:
            stocks[row['symbol']] = row['amount']

        return render_template("sell.html", stocks=stocks)

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

@app.route("/resetpassword", methods=["GET", "POST"])
@login_required
def resetpassword():
    if request.method == "POST":

        if not request.form.get("username"):
            return apology("must provide username", 403)
        elif not request.form.get("password"):
            return apology("must old provide password", 403)
        elif not request.form.get("newpassword"):
            return apology("must new provide password", 403)
        elif not request.form.get("cnewpassword"):
            return apology("must confirm new password", 403)
        elif request.form.get("newpassword") != request.form.get("cnewpassword"):
            return apology("new passwords do not match!!!", 403)

        rows = db.execute("SELECT * FROM users WHERE username = :username",username=request.form.get("username"))

        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        db.execute("UPDATE users SET hash = :newhash WHERE username = :username;",newhash=generate_password_hash(request.form.get("newpassword")), username=request.form.get("username"))

        flash("Your passowrd has been reset!")
        return redirect("/")
    else:
        return render_template("resetpassword.html")