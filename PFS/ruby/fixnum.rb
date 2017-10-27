class Fixnum
	def bit_length
		self.zero? ? 1 : Math.log(self + 1.0, 2.0).ceil
	end
end

	p 0.bit_length
	p 2.bit_length
	p fibonacci(0)

def fibonacci(n)
end