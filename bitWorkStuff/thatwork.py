def hex_letter_to_num(letter):
	if ord(letter) >= ord('0') and ord(letter) <= ord('9'):
		return ord(letter) - ord('0')
	elif ord(letter) >= ord('A') and ord(letter) <= ord('F'):
		return 10 + ord(letter) - ord('A')
	else:
		print('Invalid letter!')

def hex_to_unsigned_int(hex_num):
	ans = 0
	size = len(hex_num)

	for i in range(0, size):
		ans += hex_letter_to_num(hex_num[i]) * pow(16, size - 1 - i) 

	return ans

def hex_to_signed_int(hex_num):
	size = len(hex_num)

	bytes_count = size / 2

	unsigned = hex_to_unsigned_int(hex_num)
	power = pow(2, bytes_count * 8 - 1)

	if unsigned < power:
		return int(unsigned)
	else:
		unsigned -= power
		unsigned -= power

		return int(unsigned)

def hex_to_float(hex_num):
	size = len(hex_num)

	bytes_count = int(size / 2)
	bits = bytes_count * 8

	decimal_num = hex_to_unsigned_int(hex_num)

	binary = []

	for i in range(0, bits):
		binary.append((decimal_num >> (bits - 1 - i)) & 1)

	whole_bits = 0
	fraction_bits = 0

	if bytes_count == 1:
		whole_bits = 3
		fraction_bits = 4
	elif bytes_count == 2:
		whole_bits = 19
		fraction_bits = 6
	elif bytes_count == 3:
		whole_bits = 15
		fraction_bits = 8
	elif bytes_count == 4:
		whole_bits = 21
		fraction_bits = 10
	else:
		print('Too many bytes!')
		return

	sign = 1 if (binary[0] == 0) else -1
	whole = 0
	fraction = 0

	for i in range(0, whole_bits):
		whole += binary[whole_bits - i] * pow(2, i)

	for i in range(0, fraction_bits):
		fraction += binary[bits - 1 - i] * pow(2, i)

	exponent = whole - (pow(2, whole_bits - 1) - 1)
	mantissa = 1

	print('Binary is ')

	binary_str = ''
	for bit in binary:
		binary_str += str(bit)

	print(binary_str)

	for i in range(0, fraction_bits):
		mantissa += binary[whole_bits + 1 + i] / pow(2, i + 1)

	result = sign * pow(2, exponent) * mantissa

	return result

def main():
	hex_number = input('Insert hex here: ')
	convert_type = input('Choose conversion type (S/U/F) : ')

	if len(hex_number) > 8:
		print('Hex number is too big!')
		return

	if len(hex_number) % 2 == 1:
		hex_number = '0' + hex_number

	if convert_type == 'U':
		print(hex_to_unsigned_int(hex_number))
	elif convert_type == 'S':
		print(hex_to_signed_int(hex_number))
	elif convert_type == 'F':
		print(hex_to_float(hex_number))
	else:
		print('Invalid conversion type!')

main()