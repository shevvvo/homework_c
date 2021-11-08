import random 
 
files = ['1.txt', '2.txt', '3.txt', '4.txt', '5.txt', '6.txt'] 
count = 0 
 
while (count < 6): 
    f = open(files[count], 'w') 
    b = [':)', ':('] 
    good = 15 
    bad = 11 
    if (count == 5): 
        good = 26000000 
        bad = 27000000 
    while bad != 0 or good != 0: 
        c = random.choice(b) 
        if (c == ':)'): 
            if (good != 0): 
                good = good - 1 
                f.write(c) 
        if (c == ':('): 
            if (bad != 0): 
                bad = bad - 1 
                f.write(c) 
    f.close() 
    count = count + 1
