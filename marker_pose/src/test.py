locate = [9,6,18,15,27,30,33,21,18,6]
locate.insert(0, locate[0] - 12)
# print(locate)

def arrow(a):
    if abs(a) == 12:
        if a > 0:
            #
            return 'down'
        else:
            return 'up'

    elif abs(a) == 3:
        if a > 0:
            return 'right'
        else:
            return 'left'

#head direction
for i in range(1, len(locate)):

    head = locate[i] - locate[i-1] # 24 - 12
    direction = arrow(head)

    print(locate[i], arrow(head))
    print('direction : ', direction)
    if i == len(locate)-1:
        print('stop')
        break
    else:
        if (direction == 'down'):
            if locate[i+1] < locate[i]:
                print('turn right')
            elif locate[i+1] > locate[i]:
                print('turn left')

        if (direction =='left'):
            if locate[i+1] < locate[i]:
                print('turn right')
            elif locate[i+1] > locate[i]:
                print('turn left')

        if (direction == 'up'):
            if locate[i+1] > locate[i]:
                print('turn right')
            elif locate[i+1] < locate[i]:
                print('turn left')
        
        if (direction =='right'):
            if locate[i+1] > locate[i]:
                print('turn right')
            elif locate[i+1] < locate[i]:
                print('turn left')
    
