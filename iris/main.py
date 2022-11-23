sepal_lengh = 0
sepal_width = 1
petal_length = 2
petal_width = 3
label = 4

labels = ['Iris-setosa', 'Iris-versicolor', 'Iris-virginica']

data = None

with open("iris.data") as dataFile:
    data = dataFile.read()

data = data.splitlines()
data = [x.split(',') for x in data]

acertos = 0
erros = 0
setosa = 0

for line in data:
    line_label = line[label]
    line = [float(line[x]) for x in range(4)]
    if line_label == 'Iris-setosa':
        setosa +=1

    if (line[petal_length] <= 1.8) and (line[petal_length] >= 1.0):
        print('Iris-setosa ', end='')
        if line_label == 'Iris-setosa':
            print('(acerto)')
            acertos += 1
        else:
            print('(erro)')
            erros += 1

print(f'total setosas: {setosa}')
print(f'acertos: {acertos}, erros: {erros}, {acertos/(setosa+erros)}')