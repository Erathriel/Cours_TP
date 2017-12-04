#  ============================================================================
#
#            Prime number thread
#
#  ============================================================================
#
#  Author: J.-M. Hufflen
#  Date: February 2015
#
#  ============================================================================

class Fixnum
  def no_divisor_found?(a)
    a.all? do |presumed_divisor|
      if block_given? and yield(presumed_divisor)
        return true
      else
        self % presumed_divisor != 0
      end
    end
  end
end

$trace = true

$prime_number_thread = Thread.new do
  current = 1
  prime_number_a = []
  Thread::current[:current_prime_number] = current
  Thread::current[:prime_number_a] = prime_number_a.clone
  sleep
  loop do
    current += 1
    the_floor_sqrt = Math.sqrt(current).floor 
    if the_floor_sqrt == 1 or
        current.no_divisor_found?(prime_number_a) do |presumed_divisor|
          presumed_divisor > the_floor_sqrt
        end
      puts "#{current} got..." if $trace
      prime_number_a.push(current)
      Thread::current[:current_prime_number] = current
      Thread::current[:prime_number_a] = prime_number_a.clone
      sleep
    end
  end
end

def next_prime_number
  until $prime_number_thread.status == 'sleep'
  end
  $prime_number_thread.wakeup
  until $prime_number_thread.status == 'sleep'
  end
  $prime_number_thread[:current_prime_number]
end

def next_prime_number_after(i)
  prime_number_got =
    $prime_number_thread[:prime_number_a].find do |prime_number|
      prime_number > i
    end
  until prime_number_got
    next_prime_number_0 = next_prime_number
    prime_number_got = next_prime_number_0 > i ? next_prime_number_0 : nil
  end
  prime_number_got
end

def sumeverywhereignore1(a)
  goingeverywhere = Proc.new do |alreadysummed,a0|
    a0_class = a0.class
    if a0_class == Fixnum
      alreadysummed + a0
    else
      if a0_class == Array
        a0.inject(alreadysummed) do |alreadysummed_0,a1|
          goingeverywhere[alreadysummed_0,a1]
        end
      else
        alreadysummed
      end
    end
  end
  goingeverywhere[0,a]
end

def sumeverywhereeject(a)
  goingeverywhere = Proc.new do |alreadysummed,a0|
    a0_class = a0.class
    if a0_class == Fixnum
      alreadysummed + a0
    else
      if a0_class == Array
        a0.inject(alreadysummed) do |alreadysummed_0,a1|
          goingeverywhere[alreadysummed_0,a1]
        end
      else
        return nil
      end
    end
  end
  goingeverywhere[0,a]
end

def sumeverywhereperform(a)
  goingeverywhere = Proc.new do |alreadysummed,a0|
    a0_class = a0.class
    if a0_class == Fixnum
      alreadysummed + a0
    else
      if a0_class == Array
        a0.inject(alreadysummed) do |alreadysummed_0,a1|
          goingeverywhere[alreadysummed_0,a1]
        end
      else
        yield
      end
    end
  end
  goingeverywhere[0,a]
end

def sumeverywhereignore2(a)
  sumeverywhereperform(a) do 0 end
end

def sumeverywhereeject2(a)
  sumeverywhereperform(a) do return nil end
end

def sumeverywhereignore(array)
  if array.kind_of?(Array)
    sum = 0
    array.each do |nb|
      if nb.kind_of?(Array)
        sum += sumeverywhereignore(nb)
      elsif nb.kind_of?(Fixnum)
        sum += nb
      else
        sum += sumeverywhereignore(nb)
      end
    end
  elsif array.kind_of?(Fixnum)
    sum = array
  else
    sum = 0
  end
  sum
end


p (sumeverywhereignore1(2017))
p (sumeverywhereignore1([2017,[8,9]]))
p (sumeverywhereignore(2017))
p (sumeverywhereignore([2017,8]))
p (sumeverywhereignore('L3'))
p (sumeverywhereignore([2017,[8,9],'L3', 15]))
p (sumeverywhereeject([2017,8]))
p (sumeverywhereeject([2017,[8,9],'L3', 15]))
p (sumeverywhereperform([2017,8]))
p (sumeverywhereignore2([2017,[8,9],'L3', 15]))
p (sumeverywhereeject2([2017,[8,9],'L3', 15]))
p ((catch :exit do 
    2016+sumeverywhereperform([2017,[8,9],'L3', 15]) do throw :exit end
    end))