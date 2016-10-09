RE = list(input())
RE.append(')')
SignStack = list('(')
RPN = list()
flag = False
Sigma = list()

for item in RE:
    if item == '(':
        if flag:
            while SignStack[-1] == '*':
                RPN.append(SignStack.pop())
            SignStack.append('.')
        flag = False
        SignStack.append('(')
    elif item == ')':
        if not flag:
            SignStack.pop()
        while SignStack[-1] != '(':
            RPN.append(SignStack.pop())
        SignStack.pop()
    elif item == '|':
        while SignStack[-1] != '|' and SignStack[-1] != '(':
            RPN.append(SignStack.pop())
        SignStack.append('|')
        flag = False
    elif item == '*':
        SignStack.append('*')
        flag = True
    else:
        if flag:
            while SignStack[-1] == '*':
                RPN.append(SignStack.pop())
            SignStack.append('.')
        if item not in Sigma:
            Sigma.append(item)
        RPN.append(item)
        flag = True

NodeID = 0
EdgeList = list()
MataStack = list()
del RE
del SignStack
del flag

for item in RPN:
    if item == '.':
        TempList = [MataStack.pop(), MataStack.pop()]
        EdgeList.append([TempList[1][1], TempList[0][0], -1])
        MataStack.append([TempList[1][0], TempList[0][1]])
    elif item == '*':
        TempList = [MataStack.pop()]
        EdgeList.append([TempList[0][1], TempList[0][0], -1])
        EdgeList.append([NodeID, TempList[0][0], -1])
        EdgeList.append([TempList[0][1], NodeID+1, -1])
        EdgeList.append([NodeID, NodeID+1, -1])
        MataStack.append([NodeID, NodeID+1])
        NodeID += 2
    elif item == '|':
        TempList = [MataStack.pop(), MataStack.pop()]
        EdgeList.append([NodeID, TempList[0][0], -1])
        EdgeList.append([NodeID, TempList[1][0], -1])
        EdgeList.append([TempList[0][1], NodeID+1, -1])
        EdgeList.append([TempList[1][1], NodeID+1, -1])
        MataStack.append([NodeID, NodeID+1])
        NodeID += 2
    else:
        EdgeList.append([NodeID, NodeID+1, item])
        MataStack.append([NodeID, NodeID+1])
        NodeID += 2

Graph = [[-2] * NodeID]*NodeID
del MataStack
del NodeID
del RPN
del TempList

for item in EdgeList:
    Graph[item[0]][item[1]] = item[2]
    # Graph Error!
for item in Graph:
    print(item)

for num in range(len(EdgeList)):
    print("Edge no." + str(num))
    print(EdgeList[num])
