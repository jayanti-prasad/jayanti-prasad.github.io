import sys
import os

if __name__ == "__main__":

   with open(sys.argv[1],"r") as fp:
      data = fp.readlines()

   
   #print(data)

   count = 0
   for line in data:
       line = line.replace('\n','') 
       line = line.replace('\"','\\"') 
       line = line.replace('<li>','<br><li>') 
       if count > 27 and count < 142:
          print("+" + "\"" + line + "\"")
       count +=1


