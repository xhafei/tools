#!/usr/bin/env python
'''
this script check if the tp file's blanket are matching,
you can put this script in template folder and run it
author:rudy.xu
2017-04-20 10:53:05
'''
import os
def check_tp_blanket():
  dl = os.listdir(".")
  cr = True
  find_tp = False
  for i in dl:
    if(os.path.isdir(i)):
      print i, "*"*30
      sl = os.listdir(i)
      for j in sl:
        sp = "%s/%s" %(i,j)
        print sp
        if "tp" in j:
          find_tp = True
          with open(sp) as fo:
            count = 0
            fc = 0
            for l in fo:
              if fc < 0:
                print "tp file %s not ok, short of { ---------------------------------" % (sp)
                print "lines:%d" % (count)
  	        fc = 0
  	        cr = False
                break
              for x in l:
                if "{" in x:
                  fc+=1
                elif "}" in x:
                  fc-=1
              count+=1
  	  if fc != 0:
              print "tp file %s not ok, redundant } +++++++++++++++++++++++++++++++++" % (sp)
              print "lines:%d" % (count)
              cr = False
  if find_tp:
    if cr:
      print
      print "thank god, everything is ok"   
    else:
      print
      print "shit happens, please check it"   
  else:
    print
    print "seems not find tp file"

if __name__ == "__main__":
  check_tp_blanket()
