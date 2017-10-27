def showRE(target,regexp)
  #  Highlights with chevrons where match occurs.
  p "#{$`}>>>>#{$&}<<<<#{$'}" if target =~ regexp
end

p showRE('beginning <a>Try 1</a><a>Try 2</a> ending',/<a>.*<\/a>/)
p showRE('beginning <a>Try 1</a><a>Try 2</a> ending',/<a>.*?<\/a>/)

p showRE('beginning!nning!nning!nningending',/(.*)!\1/)
p showRE('beginning!nning!nning!nningending',/(.*?)!\1/)

p 'Little players!'.sub(/little/,'master')
p 'Little players!'.sub(/little/i,'master')

$s = 'beginning <a>Try 1</a><a>Try 2</a> ending'
p $s.sub(/(<a>.*?<\/a>)(<a>.*?<\/a>)/,'\2\1')
p $s
p $s.sub!(/(<a>.*?<\/a>)(<a>.*?<\/a>)/,'\2\1')
p $s
$r = /(<a>(?:.*?)<\/a>)*/
p $r
p $r.class
p $s.gsub($r,'<b>\1</b>')
$r0 = /<a>(.*?)<\/a>/
p $s.gsub($r0,'<b>\1</b>')

p /<a>.*<\/a>/.match($s)
p /<a>.*?<\/a>/.match($s)

m = /<a>(.*?)<\/a><a>(.*?)<\/a>/.match($s)
p m

for i in 0..2
  p m[i]
  p m.begin(i)
  p m.end(i)
end

p m.post_match
m0 = $r.match($s)
p m0
m1 = $r0.match($s)
p m1
