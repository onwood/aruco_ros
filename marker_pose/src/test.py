locate = [9,6,18,15,27,30,33,21,18,6]
def arrow(a):
    if abs(a) == 12:
        if a > 0:
            #
            return 'down'
        else:
            return 'up'

    elif abs(a) == 3:
        if a > 0:
            return 'left'
        else:
            return 'right'
    
#have to go
a = locate[2] - locate[1]
# print('have to go ', arrow(a))

#head direction
for i in range(1, len(locate)):

    head = locate[i] - locate[i-1] # 24 - 12
    direction = arrow(head)

    print(locate[i], arrow(head))
    print('direction : ', direction)

    if (direction == 'down'):
        if locate[i-1] < locate[i]:
            print('turn left')
        elif locate[i-1] > locate[i]:
            print('turn right')

    if (direction =='left'):
        if locate[i-1] < locate[i]:
            print('turn left')
        elif locate[i-1] >  locate[i]:
            print('turn right')

    if (direction == 'up'):
        if locate[i-1] > locate[i]:
            print('turn left')
        elif locate[i-1] < locate[i]:
            print('turn right')
    
    if (direction =='right'):
        if locate[i-1] < locate[i]:
            print('turn left')
        elif locate[i-1] >  locate[i]:
            print('turn right')
    
