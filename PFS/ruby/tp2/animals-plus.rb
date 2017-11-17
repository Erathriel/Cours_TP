#  ============================================================================
#  Examples of classes using Ruby --- January 2017

class Animal
  #
  attr_reader :name
  #
  def initialize(name_0)
    @name = name_0   #  "@...":  instance variable,
    @@animalnb += 1  #  "@@...": static   .........
  end
  #
  def eat
    puts 'I\'m eating.'
  end
  #
  @@animalnb = 0
  #
  def self.nb
    @@animalnb
  end
  #
  CrDate = '2016/12/13'
  #
end

class Dog < Animal
  #
  attr_reader :ownername
  #
  def initialize(name_0,ownername_0)
    super(name_0)
    @ownername = ownername_0
  end
  #
  def bark
    puts 'I\'m barking.'
  end
  #
  class << self
    undef_method :nb
  end
  #
end

class Monkey < Animal
  #
  def climb
    puts 'I\'m climbing.'
  end
  #
  class << self
    undef_method :nb
  end
  #
end

#  "$<variable-name>": global variable.
$a = Animal.new('Baloo')
$a.eat
p $a.name

$d = Dog.new('Rintintin','Bonanza')
$d.eat
$d.bark
p $d.name
p $d.ownername

$m = Monkey.new('Snow Flake')
$m.eat
$m.climb
p $m.name

p Animal.nb

$kingkong = Monkey.new('King-Kong')

def $kingkong.skullisland
  puts 'I\'m at home.'
end

class << $kingkong
  #
  def empirestatebuilding
    puts 'That\'s the end, my friend.'
  end
  #
end

p $kingkong.empirestatebuilding

class Dog
  #
  def bite
    puts 'Biting U!'
  end
  #
  def do_with_names_and(x)
    yield(@name,@ownername,x)
  end
  #
end

$d.bite

puts Animal::CrDate

class Animal
  #
  def gimme
    puts 'Gimme, gimme ' + yield
  end
  #
  def do_with_name
    puts "I'm #{@name}"
    yield(@name) if block_given?
  end
  #
end


#p $a.do_with_name("toto")

=begin
$kingkong.gimme do ' A men after midnight' end
$kingkong.gimme
$kingkong.do_with_name do |name| puts "#{$name} and Jane" end
=end
$a1 = [7,11,2017]
=begin
$a1.each do |x| p x end
$a1.each_index do |index| p index end
$a1.each_with_index do |x,index| p [x,index] end
$a1.select do |x| x.odd? end
=end

#p($a1.inject(0) do |x,y| x+y end)
#p((1..10).inject(1) do |x,y| x*y end)

class Fixnum
  def fact
    if self>0
      (1..self).inject(1) do |x,y| x*y end
      end
  end
end

n=10

p n.fact

p 10.fact