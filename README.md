Wiktor Grzankowski
------------------
Header files contain templates for classes of expedition members,
some using specialized templates and various concepts,
as well as a Treasure class. Adventurers can meet
one another on the road or find treasures, 
so in treasure_hunt.h template
Encounter simulates such meetings. Using constant 
expressions allows this program to be done fully during
compilation time. Variadic template for constexpr
function expedition allows it to sequentially
execute given encounters.
