import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from collections import Counter

def calcular_media(dados):
    dados_limpos = [x for x in dados if pd.notna(x)]  
    return np.mean(dados_limpos) if dados_limpos else 0


def calcular_mediana(dados):
    dados_limpos = [x for x in dados if pd.notna(x)]  
    return np.median(dados_limpos) if dados_limpos else 0


def calcular_moda(dados):
    dados_limpos = [x for x in dados if pd.notna(x)]  
    if not dados_limpos:
        return 0
    contador = Counter(dados_limpos)
    return contador.most_common(1)[0][0]


def ler_csv(nome_arquivo):
    try:
        df = pd.read_csv(nome_arquivo, sep=';')
        return df
    except Exception as e:
        print(f"Erro ao abrir o arquivo: {e}")
        return None


def main():
    nome_arquivo = "Cafe.csv"  
    df = ler_csv(nome_arquivo)

    if df is None or df.empty:
        print("Nenhum dado válido encontrado no arquivo!")
        return


    quantidades_xicaras = {
        "Uma Xícara": 1,
        "Duas Xícaras": 2,
        "Três Xícaras": 3,
        "Quatro Xícaras": 4,
        "Cinco Xícaras": 5,
    }
    
    quantidades_acucar = {
        "Pouca Açúcar": 1,
        "Muita Açúcar": 3,
        "Sem Açúcar": 0,
    }

    preferencia_cafe = {
        "Capuccino": 1,
        "Café Preto": 2,
        "Latte": 3,
    }

    preferencia_acucar = {
        "Açúcar Normal": 1,
        "Açúcar Mascavo": 2,
    }

    preferencia_cafeteria = {
        "Starbucks": 1,
        "Pão de Açúcar": 2,
        "Delta Café": 3,
        "Cafeteria Santa Clara": 4,
        "Cafeteria São Braz": 5,
        "Boutique Café Cordeiro": 6,
    }


    cafe_preferido = df['Entre essas bebidas, qual você prefere ?'].map(preferencia_cafe).tolist()
    quant_xicaras = df['Quantas xícaras você toma ?'].map(quantidades_xicaras).tolist()
    quant_acucar = df['Você prefere ?'].map(quantidades_acucar).tolist()
    acucar_preferido = df['Qual açúcar você escolhe ?'].map(preferencia_acucar).tolist()
    cafeterias_favoritas = df['Qual sua cafeteria favorita ?'].map(preferencia_cafeteria).tolist()


    quant_xicaras = [x for x in quant_xicaras if pd.notna(x) and x > 0]
    quant_acucar = [x for x in quant_acucar if pd.notna(x)]
    cafe_preferido = [x for x in cafe_preferido if pd.notna(x)]
    acucar_preferido = [x for x in acucar_preferido if pd.notna(x)]
    cafeterias_favoritas = [x for x in cafeterias_favoritas if pd.notna(x)]

    
    print("Resultados para a quantidade de xícaras:")
    print("Média:", calcular_media(quant_xicaras))
    print("Mediana:", calcular_mediana(quant_xicaras))
    print("Moda:", calcular_moda(quant_xicaras))

    print("\nResultados para a quantidade de açúcar:")
    print("Média:", calcular_media(quant_acucar))
    print("Mediana:", calcular_mediana(quant_acucar))
    print("Moda:", calcular_moda(quant_acucar))

    print("\nResultados para preferências de café:")
    print("Média:", calcular_media(cafe_preferido))
    print("Mediana:", calcular_mediana(cafe_preferido))
    print("Moda:", calcular_moda(cafe_preferido))

    print("\nResultados para preferências de açúcar:")
    print("Média:", calcular_media(acucar_preferido))
    print("Mediana:", calcular_mediana(acucar_preferido))
    print("Moda:", calcular_moda(acucar_preferido))

    print("\nResultados para cafeterias favoritas:")
    print("Média:", calcular_media(cafeterias_favoritas))
    print("Mediana:", calcular_mediana(cafeterias_favoritas))
    print("Moda:", calcular_moda(cafeterias_favoritas))

    plt.figure(figsize=(12, 8))

    plt.subplot(2, 2, 1)
    n, bins, patches = plt.hist(quant_xicaras, bins=np.arange(0.5, 6.5, 1), color='r', alpha=0.7, edgecolor='black', width=0.6)
    plt.title("Distribuição de Xícaras")
    plt.xlabel("Quantidade de Xícaras")
    plt.ylabel("Frequência")
    plt.xticks(range(1, 6))

    for count, x in zip(n, bins):
        plt.text(x + 0.1, count, str(int(count)), va='bottom')

    plt.subplot(2, 2, 2)
    n, bins, patches = plt.hist(quant_acucar, bins=np.arange(-0.5, 4.5, 1), color='g', alpha=0.7, edgecolor='black', width=0.6)
    plt.title("Distribuição de Açúcar")
    plt.xlabel("Quantidade de Açúcar => Pouca Açúcar: 1 - Muita Açúcar: 3 - Sem Açúcar: 0")
    plt.ylabel("Frequência")
    plt.xticks(range(0, 4))

    
    for count, x in zip(n, bins):
        plt.text(x + 0.1, count, str(int(count)), va='bottom')

    
    plt.subplot(2, 2, 3)
    n, bins, patches = plt.hist(cafe_preferido, bins=np.arange(0.5, 4.5, 1), color='b', alpha=0.7, edgecolor='black', width=0.6)
    plt.title("Preferências de Café")
    plt.xlabel("Tipo de Café => Capuccino: 1 - Café Preto: 2- Latte 3" )
    plt.ylabel("Frequência")
    plt.xticks(range(1, 4))

    
    for count, x in zip(n, bins):
        plt.text(x + 0.1, count, str(int(count)), va='bottom')

    
    plt.subplot(2, 2, 4)
    n, bins, patches = plt.hist(cafeterias_favoritas, bins=np.arange(0.5, 7.5, 1), color='m', alpha=0.7, edgecolor='black', width=0.6)
    plt.title("Cafeterias Favoritas")
    plt.xlabel("Cafeterias => Starbucks: 1 -Pão de Açúcar: 1 -Delta Café:2 -Cafeteria Santa Clara 4- Cafeteria São Braz 5-Boutique Café Cordeiro : 6")
    plt.ylabel("Frequência")
    plt.xticks(range(1, 7))

    
    for count, x in zip(n, bins):
        plt.text(x + 0.1, count, str(int(count)), va='bottom')

    plt.tight_layout()  
    plt.show()  

if __name__ == "__main__":
    main()