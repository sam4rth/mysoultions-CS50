from cs50 import get_int

card = 0


# substitution
# checksum -> sum of the digits, lsum
# length -> swi

while (card < 100):
    card = get_int("Number : ")

scard = str(card)
length = len(scard)
checksum = 0
# for i in range(length, 0, -1):
#     if swi % 2 == 0:

for i in range(length):

    if ((length - i) % 2 == 0):
        if ((int(scard[i]) * 2) >= 10):
            checksum = checksum + int((int(scard[i]) * 2) / 10) + int((int(scard[i]) * 2) % 10)
        else:
            checksum = checksum + (int(scard[i]) * 2)
    else:
        checksum = checksum + int(scard[i])

if (checksum % 10 == 0):
    if (length == 13 or length == 14 or length == 15 or length == 16) and (int(scard[0]) == 4):
        print("VISA")
    elif (length == 16 and int(scard[0]) == 5 and (int(scard[1]) <= 5 and int(scard[1]) >= 1)):
        print("MASTERCARD")
    elif (length == 15 and int(scard[0]) == 3 and (int(scard[1]) == 3 or int(scard[1]) == 7)):
        print("AMEX")
    else:
        print("INVALID")
else:
    print("INVALID")