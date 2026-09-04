"""

relationship matrix + (side + sequece data)


+F : current , +2 +1 -2 -1 -> for current rotate 90 degree , but for each rest , move their rightmost vertical up and take data from Their own -1 again
fundamentally the difference between slice and rotate face is , the current is treated specially in face rotate
rest , we are fetching the data from below and moving up
-1

for slice if we had a +E and not a -E then for + ,

we do +E : current , +2 , 3 , -2 ,-> each's middle data moves up , for each take THEIR own -2's middle to update the current state

"""


