# AdventOfCode-2022

I'm gonna be using this to relearn C++ (focusing on C++17) and data structures / algorithms. Hopefully I'll be able
to follow the rhythm. I don't expect to get the most optimal solution, just something that works (and day by day reducing
the awkwardness of coding in C++).

## Log
### Day 01
No surprises here since, being the first day, I expected it to be easy, coding wise. These first days will be used to gain back the C++ feel
after so many years and gather some of the utilities that will become useful for the following days.

### Day 02
I didn't want to think much about it and possibly ending with a *clever* over-engineered solution that would work for both parts and 
went straight to use a `std::unordered_map` linking each possible combination with the outcome result for both parts.

### Day 03
It might be too soon already, but I'm beginning to feel my rustiness when it comes to algorithms and data structures. For the first part, I had
the idea of using a `std::unordered_map` for each of the *rucksack*'s compartment and check for maximum occurrence, but I disregarded it 
and went with a `std::set` to do intersection. 
Then for the second part I decided to bring back my first idea. The algorithm might not be pretty, neither am I. Might come back to it later on.

Tiny improvement made replacing the inner loop in the first part by a `std::set` initialization using *rucksack*
substring. Thanks, [Nacho](https://github.com/nlasheras/aoc-2022), for the tip.

### Day 04
When looking at the input, a conversation just came to my mind which I had 2 weeks ago about the allegedly lack of support for regex on C++ (which
actually were included for *C++11*. With that parsing was really easy.

### Day05
First real challenge for the input. Once again, regex came to help for the second part of the input. But the first part, oh boy, that was *fun*.
I tried matching the last line to obtain the number of crates (took me a while), and then come to the realization I wouldn't be able to use it
for how I was trying to parse. From bottom to top. The fun part came when, although everything was working as intended, the answer wasn't correct.

Long story short, *-fsanitize=undefined -fsanitize=address* and never ever again copy-pasting the input to the editor... which trimmed the lines.

### Day06
By far the easiest problem so far (or perhaps I'm bit more used to the language). Made two different solutions, the first one using a regexp generator.
And for the second one I used a sliding window initializing a temporal set to check for uniqueness.
Regexp solution is overkill and grows exponentially with the window size... and it led me to a nice *call-it-bug* or unimplemented *undefined behaviour* 
in *libc++* (using clang over macOS here). As it turns out, *libc++* doesn't support back references: *libc++abi: terminating due to uncaught exception of type std::__1::regex_error: The expression contained an invalid back reference.* *Libstdc++*, on the other hand, does support them.
