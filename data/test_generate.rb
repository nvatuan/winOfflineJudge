
workingdir = "D:/P/$rc_code/!Github/lorem-ipsum/data/P#0006"
Dir.chdir("#{workingdir}/testcases")

cases = 1
start = 30

cases.times do |c|
	f = File.new("in#{c+start}", "w")
	
=begin
	f.write( 1 )
	3.times do
		17.times do
			f.write( rand(10) )
		end
		f.write(' ')
	end
=end
	a = 1000
	b = 1000
	f.write("#{a} #{b}")
	a.times{
		f.write("\n")
		b.times{
			if rand(3) == 0
				f.write('W')
			else
				f.write('D')
			end
		}
	}
#	string.split("").each{ |c|
#		bin = c.ord().to_s(2)
#		(8-bin.length).times do 
#			f.write(0)
#		end
#		f.write(bin)
#	}

	f.close

	`type in#{c+start} | source0006.exe > out#{c+start}`
end
