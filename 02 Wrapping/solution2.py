print("%.0f\n%.0f" %
	(lambda x:(x.real, x.imag))(sum(3 * a * b + 2 * b * c + 2 * a * c + 1j * (2 * (a + b) + a * b * c)
		for a, b, c in (sorted(map(int, x.split("x"))) for x in open("input.txt")))))