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


### Day 05
First real challenge for the input. Once again, regex came to help for the second part of the input. But the first part, oh boy, that was *fun*.
I tried matching the last line to obtain the number of crates (took me a while), and then come to the realization I wouldn't be able to use it
for how I was trying to parse. From bottom to top. The fun part came when, although everything was working as intended, the answer wasn't correct.

Long story short, *-fsanitize=undefined -fsanitize=address* and never ever again copy-pasting the input to the editor... which trimmed the lines.


### Day 06
By far the easiest problem so far (or perhaps I'm bit more used to the language). Made two different solutions, the first one using a regexp generator.
And for the second one I used a sliding window initializing a temporal set to check for uniqueness.
Regexp solution is overkill and grows exponentially with the window size... and it led me to a nice *call-it-bug* or unimplemented *undefined behaviour* 
in *libc++* (using clang over macOS here). As it turns out, *libc++* doesn't support back references: *libc++abi: terminating due to uncaught exception of type std::__1::regex_error: The expression contained an invalid back reference.* *Libstdc++*, on the other hand, does support them.


### Day 07
I was really tempted of parsing the input on a tree. Ended up making use of a `std::stack` of filesnames (with full path) to track position and a 
`std::unordered_map` to store the sizes of each directory.


### Day 08
First idea was to create a grid where I'd store boolean telling whether that tree was visible from any of the 4 directions, so I could check afterwards 
and count. It was easier to just return a boolean from each of the direction checks and then increase the counter.

For the second part, initially the score was wrong because I wasn't using the ranges properly, counting always from edges to the tree. Once I reversed it, everything came together. Each of the direction checks now returns a `std::pair` with visibility and the amount of trees visible from that tree.

A next iteration would be perhaps to use an array for data locality.


### Day 09
At first I thought the problem was a bit more complicated than it was. I had understood the bridge had a fixed width, then horizontal positions would 
have to be moduled when trespassing the edges. For the different moves, regex came again and then it was just a matter of dividing the different 
positions of the tail in regard of the head and how it should move.

For the second part I just refactored to a function checking relative positions of two knots and move accordingly. Then all the knots are in a vector, 
making it usable for any amount of knots.


### Day 10
One of those days on which you read *part 1* and think: it's a trap! It can't be that simple. Then go to *part 2*, start reading... 

(ノಠ益ಠ)ノ彡┻━┻ 

On a second reading it was simpler than thought.

For the first part I used an `std::unordered_set` to check for the significant *signals*. Then working on the second one, I realised it was simpler to
use modules since signals are `mod 40` displaced by 20.

Testing the output was bit trickier for the second part, I was having some issues with one missing or extra pixel or even extra line.


### Day 11
Most of the work went into parsing, which was quite verbose. Have to consider whether regex are the right option the way I used them or
try to fiddle with *scanf*.

The first part was quite straightforward. For the second, some thought had to be done since the worry levels get unusable really quick. Didn't want
to go into *BigInt* territory. A quick way was to just multiply all monkey's divisibility checks and use that as module, that way any resulting worry 
level would still be divisible by at least one of them. Given that they are prime numbers, the result is the same as getting the *Least Common Multiple*.


### Day 12
It's finally here, the shortest path problem. First idea was to implement *A\** using the *Manhattan distance* as an heuristic. Somewhere along the way
I ended up implementing *BFS* and brute force finding the shortest of the shortest paths on the second part. A good improvement to that will be inverting
the start and end point in the second part (starting at the top).

I might revisit this in the future and try the *A\** implementation.


### Day 13
Today was quite an interesting day. I initially had no clue how to implement it properly in *C++*. So I went and thought how the main part would be 
written in [swift](https://github.com/jrpinteno/AdventOfCode-2022/blob/main/13/Packet.swift) (the commented code was the first version which had a bug, more on that later).

I wanted something similar in *C++*, after asking two friends, realised that `std::variant` was the answer to my prayers. It needed a bit of tinkering to get it properly working. As it turns out, it can be used as a [base type](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2162r0.html). 
Next step was overriding `operator<()` following the schema I had done in swift. The first part worked flawlessly. But, on the second part, a wild infinite loop appeared.

I made a second implementation using `std::visit`. That's when I have realized that both my *Swift* and *C++* code had the same bug. Since I was using  `std::lexicographical_compare`, it already took care of the empty cases ([]) for the lists. Once I removed that in the first implementation, that one worked as well.


### Day 14
This has been by far the most troublesome problem... but it wasn't due to code at all. I got stranded in Nuremberg by Lufthansa (f*ck them) due to "snow storm". Part 1 was quite easy and I coded the whole thing while I was in the plane waiting for them to decide whether we could disembark. As for the second part I had some issue which was solved while I was rubberducking with a professional curling player who happened to be computer science student as well.


### Day 18
Haven't had the mindset these last days, as you can see days 15-17 haven't been done yet. It took me 2 days to fly and this was the least of my problems.
It did help though to keep my mind occupied. Wasn't as difficult as I first considered it, but some nasty accumulation of off-by-one errors prevented a quick resolution.


### Day 20
Another quite straightforward problem. Looks like I'm getting the hang of these kind of challenges. But sometimes they bite back. Instead of doing the *euclidean reminder* I thought it was clever to just iterate until the value was positive. Didn't think much of it and part 2 took around half a second per iteration on release... After some profiling I found out my cleverness wasn't such, numbers were too big. Once implemented it the right way, solution came immediately.


### Day 21
I was getting [day 13](#day-13) vibes. I knew variants was what I wanted to use. Then it was just a matter of going recursively until a monkey yelled a number.
For part 2 I knew what was asked of me, but still couldn't find a proper way of attacking the problem. Then considered *Newton-Raphson* method which I had learned in computational physics. Ended up doing *secant method* since it's more flexible and I didn't want to deal with derivatives. I still want to think another way to solve this.


### Day 23
As soon as I read half of the text I thought of using a `std::unordered_set` to hold the elf positions (à la [day 14](#day-14) with the rocks and the sand). The possible moves is a `std::unordered_map` holds the future locations as key and a vector of the elves which would move there. That way we can easily tell
when there will be collisions and those elves won't move. Finally using the *bounding box* method from [day 18](#day-18) saves the day.
