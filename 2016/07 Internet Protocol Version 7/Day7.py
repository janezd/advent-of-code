def palindrom(o):
    #print(o)
    for i,crka in enumerate(o[:len(o)-3]):
        preveri = o[i:i+4]
        print(preveri)
        if (preveri == preveri[::-1])and(o.count(o[0]) != 4):
      #      print(preveri,"preveri")
            return True
    return False

besedilo = open("Day7.txt").read().strip()
besedilo = besedilo.split("\n")
#besedilo = ["abba[mnop]qrst","abcd[bddb]xyyx","aaaa[qwer]tyui","ioxxoj[asdfgh]zxcvbn"]

counter = 0

ip = "leygxteqdwiqyxf[xswsevnmiejuyzpwf]ufuucwyuoggkkggm[yxkivwuqyqzcuuspecj]zlxqdstoausbpeki"

if True:
#for ip in besedilo:
    beseda = ""
    v_oklepaju = False
    izven_oklepaja = False

    for crka in ip:

        if crka == "[":  #konca se del, v katerem "mora" biti palindrm
            print(beseda)
            if palindrom(beseda):
                print("je")
                izven_oklepaja = True  #v tem delu besedila je palindrom
            beseda = ""

        elif crka == "]":  #konca se del, v katerem ne sme biti palindroma
            if palindrom(beseda):
                v_oklepaju = True
            beseda = ""

        else:
            beseda += crka  #ni čas za preverjanje. samo dodamo crko
     #   print(beseda)
    if palindrom(beseda): #da pogleda zadnjo besedo
        izven_oklepaja = True

    print(ip,izven_oklepaja,v_oklepaju)
    if (izven_oklepaja)and(not v_oklepaju):
        counter += 1
        print(ip)
        #print("jeej")

print(counter)
