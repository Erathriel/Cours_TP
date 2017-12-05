def iterate(n,x)
	sum = x
	n.times do
		sum += 1
	end
	return sum
end

p iterate(0,2017)
p iterate(10,2017)

class Array
	def included_into?(a0)
		size = 0
		self.each do |elem|
			if a0.include?(elem)
				size += 1
			end
		end
		if size == self.size
			true
		else
			false
		end
	end

	def same_elements_than?(a0)
		if self.included_into?(a0) && a0.included_into?(self)
			true
		else
			false
		end
	end

	/def right_inject(init)
		
	end/
end

p([4,12,2017].included_into?([11,12,4,2017])) 
p([4,12,2017].included_into?([11,12,5,2017]))

p([4,12,2017].same_elements_than?([11,12,4,2017]))
p([4,12,2017].same_elements_than?([12,4,12,2017]))
p([12,4,12,2017].same_elements_than?([12,4,12,2017]))

def robustsort(a)
	if a.all? {|elem| elem.class == Fixnum}
		return a.sort
	else
		return nil
	end
end

def match_french_postcode(s)
	if s.length != 5
		false
	end
end

p robustsort([])
p robustsort([12,4,2017])
p robustsort([12,"Decembre",2017])