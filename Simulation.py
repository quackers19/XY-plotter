from re import U
import gcode_parser
import turtle

turtle.speed(0)
turtle.hideturtle()
turtle.penup()
turtle.color("green")

cmdlist = gcode_parser.cmdlist()
print(cmdlist)

#print expected output
for cmd in cmdlist:
    if 'penu' in cmd:
        turtle.penup()
        print('pen up')
    elif 'pend' in cmd:
        turtle.pendown()
        print('pen down')
    elif 'X' in cmd:
        x_char_pos = cmd.find('X')
        y_char_pos = cmd.find('Y')
        new_x = cmd[x_char_pos + 1:y_char_pos]
        new_y = cmd[y_char_pos + 1:]
        print(new_x)
        print(new_y)
        turtle.goto(float(new_x), float(new_y))
    else:
        continue



turtle.done()

