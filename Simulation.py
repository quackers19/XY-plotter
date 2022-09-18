from re import U
import gcode_parser
import turtle
import time

turtle.speed(0)
turtle.hideturtle()
turtle.penup()
cmdlist = gcode_parser.cmdlist()
print(cmdlist)

for cmd in cmdlist:
    if cmd[3] == "u":
        turtle.penup()
        print('pen up')
    elif cmd[3] == "d":
        turtle.pendown()
        print("down")
    elif cmd[4] == "x":
        print("x")
    else:
        continue
