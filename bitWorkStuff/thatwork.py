def hex_letter_to_num(letter): # give decimal value of hex character
	if ord(letter) >= ord('0') and ord(letter) <= ord('9'): # letter is between '0' and '9'
		return ord(letter) - ord('0') # distance from '0' which is same as decimal value
	elif ord(letter) >= ord('A') and ord(letter) <= ord('F'): # letter is between 'A' and 'F'
		return 10 + ord(letter) - ord('A') # distance from 'A' + 10, which is same as decimal value
	else:
		print('Invalid letter!')

def hex_to_unsigned_int(hex_num): # turn hex number into unsigned int
	ans = 0
	size = len(hex_num) # number of characters

	for i in range(0, size): # go through each letter
		ans += hex_letter_to_num(hex_num[i]) * pow(16, size - 1 - i) # adding decimal value of letter multiplied by power of 16 (hex is base 16)

	return ans

def hex_to_signed_int(hex_num): # turn hex number into signed int
	size = len(hex_num) # number of characters

	bytes_count = size / 2 # 1 byte per 2 characters

	unsigned = hex_to_unsigned_int(hex_num) # get the decimal representation of hex number
	power = pow(2, bytes_count * 8 - 1) # leftest bit equal to 1

	if unsigned < power: # leftest bit is 0, therefore number is positive
		return int(unsigned)
	else: # leftest bit is 1 so number is negative
		unsigned -= power # remove leftest bit
		unsigned -= power # convert to negative number

		return int(unsigned)

def hex_to_float(hex_num): # turn hex number to float
	size = len(hex_num) # number of characters

	bytes_count = int(size / 2) # 1 byte per 2 characters
	bits = bytes_count * 8 # 8 bits per 1 byte

	decimal_num = hex_to_unsigned_int(hex_num) # decimal version of hex number

	binary = [] # list of bits

	for i in range(0, bits):
		binary.append((decimal_num >> (bits - 1 - i)) & 1) # add each bit

	whole_bits = 0 # number of exponent bits
	fraction_bits = 0 # number of bits after the dot

	if bytes_count == 1:
		whole_bits = 4
		fraction_bits = 3
	elif bytes_count == 2:
<<<<<<< HEAD
		whole_bits = 9
		fraction_bits = 6
=======
		whole_bits = 6
		fraction_bits = 9
>>>>>>> c39b72081fabd143e48b61c06737fb5165051808
	elif bytes_count == 3:
		whole_bits = 8
		fraction_bits = 15
	elif bytes_count == 4:
		whole_bits = 10
		fraction_bits = 21
	else:
		print('Too many bytes!')
		return

	sign = 1 if (binary[0] == 0) else -1 # if first bit is 0, positive number, else negative number
	whole = 0 # exponent bits represented as a decimal number
	fraction = 0 # bits after dot represented as a decimal number

	# print(binary) for debugging

	for i in range(0, whole_bits):
		power = pow(2, i)
		# if binary[whole_bits - i] == 1: #  for debugging
		#	print('Adding ' + str(power) + ' to ' + str(whole) + ' and getting ' + str(power + whole)) #  for debugging
		whole += binary[whole_bits - i] * pow(2, i)

	for i in range(0, fraction_bits):
		fraction += binary[bits - 1 - i] * pow(2, i)

	# print('Whole is ' + str(whole))       #  for debugging
	# print('Fraction is ' + str(fraction)) #  for debugging

	bias = pow(2, whole_bits - 1) - 1 # bias
	exponent = whole - bias
	mantissa = 1 - binary[0] # 1 for positive, 0 for negative

	for i in range(0, fraction_bits):
		mantissa += binary[whole_bits + 1 + i] / pow(2, i + 1) # add fractional parts to mantissa

	# print('Exponent is ' + str(exponent)) # for debugging
	# print('Mantissa is ' + str(mantissa)) # for debugging

	if binary[0] == 1: # is a negative number
		exponent += 1 # raise exponent by one

	result = sign * pow(2, exponent) * mantissa # calculate final result

	return result

def main():
	hex_number = input('Insert hex here: ')
	convert_type = input('Choose conversion type (S/U/F) : ')

	if len(hex_number) > 8:
		print('Hex number is too big!')
		return

	if len(hex_number) % 2 == 1:
		hex_number = '0' + hex_number # if there are odd characters, append '0' to the start

	if convert_type == 'U':
		print(hex_to_unsigned_int(hex_number))
	elif convert_type == 'S':
		print(hex_to_signed_int(hex_number))
	elif convert_type == 'F':
		print(hex_to_float(hex_number))
	else:
		print('Invalid conversion type!')

main()