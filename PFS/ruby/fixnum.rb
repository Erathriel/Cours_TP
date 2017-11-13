class Fixnum
	def bit_length
		self.zero? ? 1 : Math.log(self + 1.0, 2.0).ceil
	end
end

	p 0.bit_length
	p 2.bit_length
	p fibonacci(0)

def fibonacci(n)
	left = 0
	right = 1
	counter = 0
	while counter <= n
		left,right = right,right+left
		counter += 1
	end
	right
end