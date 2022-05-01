# Prototipo de convertor de bases numéricas

def digit_to_char(num: int) -> str:
    """Convierte un número entero a una letra

    Args:
        num (int): Número entero a convertir
    """
    if num >= 0 and num <= 9:
        return str(num)
    return chr(num + 65 - 10)


def char_to_int(num: str) -> int:
    """Convierte una letra a su valor numérico

    Args:
        num (str): Letra a convertir
    """
    if ord(num) >= 65 and ord(num) <= 90:
        return ord(num) - 65 + 10
    else:
        try:
            return int(num)
        except ValueError:
            print(f"Error: No se puede convertir el caracter \"{num}\" a un número")
            return 0

def decimal_to_base(num: int, base: int) -> str:
    """Numero decimal a un string en la base numérica especificada
    
    Args:
        num (int): Número decimal a convertir
        base (int): Base a convertir
    """
    output: str = ""
    while num!=0:
        modulo = num % base
        output += digit_to_char(modulo)
        if modulo > 0:
            num -= modulo
        num = num//base
        
    return output[::-1]

def num_to_int(string: str, base: int) -> int:
    """Convierte una cadena de caracteres a un número entero
    
    Args: 
        num (str): Cadena de caracteres a convertir
        base (int): Base a convertir
    """
    # Limpiar el string
    string = string.upper()
    string = string.replace(" ", "")
    # Invertir el orden de los caracteres
    string = string[::-1]
    result = [0 for i in range(len(string))]
    # ^^ Arreglo de ceros para almacenar los resultados

    for i, char in enumerate(string):
        result[i] = char_to_int(char)*(base**i)

    return sum(result)

def num_to_base(string: str, base: int, output_base: int) -> str:
    """Convierte un número entero a un string en la base numérica especificada
    
    Args:
        num (int): Número entero a convertir
        base (int): Base a convertir
        output_base (int): Base de salida
    """
    return decimal_to_base(num_to_int(string, base), output_base)
        

if __name__ == '__main__':
    print("Convertor de bases numéricas")
    result = num_to_base("FF", 16, 10)
    print(f"(FF)_16 = ({result})_10")

    print("")
    result = num_to_base("45", 16, 2)
    print(f"(45)_16 = ({result})_2")
    print(f"({result})_2 = ({num_to_base(result, 2, 8)})_8")
    result = num_to_base(result, 2, 8)
    print(f"({result})_8 = ({num_to_base(result, 8, 12)})_12")
    result = num_to_base(result, 8, 12)
    print(f"({result})_12 = ({num_to_base(result, 12, 25)})_25")
    result = num_to_base(result, 12, 25)
    print(f"({result})_25 = ({num_to_base(result, 25, 10)})_10")
    result = num_to_base(result, 25, 10)
    print(f"({result})_10 = ({num_to_base(result, 10, 16)})_16")


    

