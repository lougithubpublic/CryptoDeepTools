# progs第三列位数
map_third_0 = [0,-2,-3,1]
map_third_1 = [0,-2,-3,1]
map_third_2 = [0,-2,-3,1]
map_third_3 = [0,-2,-3,1]
map_third_4 = [0,-2,-3,1]
map_third_5 = [0,-2,-3]
map_third_6 = [0,-2,-3]
map_third_7 = [0,-2,-3]
map_third_8 = [0]
map_four_0 = [0,-1,-3]
map_four_1 = [0,-1]
result=[]
def has_non_zero_after_zero(arr):
    found_zero = False
    for num in arr:
        if found_zero and num != 0:
            return True
        if num == 0:
            found_zero = True
    return False

part1=[]
for  a in map_third_0:
  for b in map_third_1:
    for c in map_third_2:
      for d in map_third_3:
        for e in map_third_4:
          for f in map_third_5:
            for g in map_third_6:
               for h in map_third_7:
                 for i in map_third_8:
                    # 去除0在中间的情况
                    arr = [a,b,c,d,e,f,g,h,i]
                    if not has_non_zero_after_zero(arr):
                      if(arr[0]==1800 and arr[1]==1800):
                        pass
                      else:
                        part1.append(arr)
part2=[]            
for  a in map_four_0:
  for b in map_four_1:
     arr = [a,b,0,0]
     if not has_non_zero_after_zero(arr) and -1 in arr:
        if (arr[0]==-1 and arr[1]==-1):
          pass
        else:
          part2.append(arr)
result =[]
count =1
for item1 in part1:
  for item2 in part2:
    result.append(["","name_"+str(count),item1,item2])
    count=count+1

f = open("05VulnerableOpenSSL/progs.txt", "w")
for item in result:
  f.writelines(str(item).replace("'","\"").replace("[","{").replace("]","}")+","+"\n")

