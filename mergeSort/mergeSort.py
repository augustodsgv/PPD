
# O objetivo aqui é juntar dois vetores já ordenados internamente de forma a mantê-los ordenados
# Seja vet1 [1, 3, 5] e vet2 [2, 4, 6]
# vetAux = min(vet1[0], vet2[0])
def intercala(vet1, vet2):
    vetAux = []
    # Intercalando os valores de forma crescente, pegando sempre o valor do menor elemento do inicio dos dois vetores
    while len(vet1) > 0 and len(vet2) > 0:
        if vet1[0] < vet2[0]:
            vetAux.append(vet1.pop(0))
        else:
            vetAux.append(vet2.pop(0))

    #  Terminando o resto dos vetores
    while len(vet1) > 0:
            vetAux.append(vet1.pop(0))
    while len(vet2) > 0:
            vetAux.append(vet2.pop(0))
    return vetAux


vet1 = [1, 3, 5, 7]
vet2 = [2, 4, 6, 8]

print(intercala(vet1, vet2))