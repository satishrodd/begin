import os
print("hi")
#f = os.open('debugpimall.log', os.O_RDONLY)
f = os.open("C:\\Users\esatrod\Documents\py\\begin\debugpimall.log",os.O_RDONLY)
print(f.read(20))
