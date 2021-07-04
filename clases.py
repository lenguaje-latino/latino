class Triangulo:
    base = 0
    altura = 0

    def __init__(self, a, b):
        self.base = b
        self.altura = a

    def area(self):
        return (self.base*self.altura)/2

x = Triangulo(2, 3)
print("%s %s" % ("base: ", x.base))
print("%s %s" % ("altura: ", x.altura))
print("%s %s" % ("el area del triangulo es: ", x.area()))