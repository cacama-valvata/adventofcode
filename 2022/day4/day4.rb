require 'set'

pairs_subset = 0

IO.foreach "day4.in" do | linebuf |
    ranges = linebuf.scan /\d+/

    elf1 = (ranges[0]..ranges[1]).to_set
    elf2 = (ranges[2]..ranges[3]).to_set

    if elf1.subset? elf2 or elf2.subset? elf1
        pairs_subset += 1
    end
end

puts "PART A: #{pairs_subset} pairs"

pairs_intersect = 0

IO.foreach "day4.in" do | linebuf |
    ranges = linebuf.scan /\d+/

    elf1 = (ranges[0]..ranges[1]).to_set
    elf2 = (ranges[2]..ranges[3]).to_set

    if elf1.intersect? elf2
        pairs_intersect += 1
    end
end

puts "PART B: #{pairs_intersect} pairs"