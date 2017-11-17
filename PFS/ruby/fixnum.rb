=begin

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

=end

def american_date_2_french_date(s)
	r = /([0-9]{4})-([0-9]{2})-([0-9]{2})/
	if r=~ s
		s.sub(r,'\3/\2/\1')
	else
		r = /([0-9]{2})-([0-9]{2})-([0-9]{4})/
		if r =~ s
			s.sub(r,'\2/\1/\3')
		else
			s
		end
	end
end

def american_date_2_french_date!(s)
	unless s.sub!(/([0-9]{4})-([0-9]{2})-([0-9]{2})/,'\3/\2/\1')
		s.sub!(/([0-9]{2})-([0-9]{2})-([0-9]{4})/,'\2/\1/\3')
	end
	s
end

=begin
p american_date_2_french_date('2014-10-01')
p american_date_2_french_date('19-01-2014')
p american_date_2_french_date('10-01-20')

p american_date_2_french_date!('2014-10-01')
p american_date_2_french_date!('19-01-2014')
p american_date_2_french_date!('10-01-20')
=end

def update_your_dapartement(s)
	replacement = '25'
	groupe = '\1' + replacement
	s.sub(/\A24\z/,replacement).sub(/\A24/,replacement).sub(/(\D)24\z/,groupe).sub(/(\D)24/,groupe)
end

=begin
p update_your_dapartement('24')
p update_your_dapartement('The 24')
p update_your_dapartement('24th departement')
p update_your_dapartement('The 24th departement')
p update_your_dapartement('124th departement')
=end

def target_p(s)
	if m= /(\(.*\)\s*)++\./.match(s)
		m[0]
	end
end

p target_p('(H A B) (D E F). (G H I).')
p target_p('(H A B) (D E F). (G H I)')