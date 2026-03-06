#Character 
#gameplay 
#Commands 

[[Player]] has its own Commentary about happenings .  [[Commentary]]ies can appear on different [[Command]]s . Mainly the can be received on [[Look]] command and once player exits [[Room]]. With game progress and [[Loop stack]] numbers rises commentaries on same things need to change .
Commentaries can change completely or small parts of them can be different . For example when player try to exit from room for first time and commits [[Loop]] the can say : 
	" Hmm  ... strange this room looks like almost same as previous one ? Could it bee... ". 
for the second time they will say : 
	"What is going on ? how it could be ? is it a long corridor with same rooms or i am going insane?"
third time the commentary will be continue from now on till [[Game-Over]] event :
	"IS THIS A JOKE!? OR IS SOME KIND OF SOCIAL EXPERIMENT!!? LET ME OUT!!!"
This will give person who play more deep experience. 

Other than that as mentioned comment of player will appear mostly on [[Look]] command. This is the main way player can connect and track what is going on in game . When game start first and player spawns at center and look command prompted player will describe room in such way :
	"This is some kind of  transition back side room ? i need to escape out of here at once . There is door with Exit sign surely i need to go there" 
When player commits loop and enter the same room next time player prompts look the comment will be more detailed :
	"This is the same back side room . Nothing special . Same door in middle far with EXIT sign. Near right wall center there two dumpsters blue one for recycle other black for all type of garbage . In Right far corner on top i can see CCTV cameras indicator blinking. Some body forget this damn chair in middle of room. on left wall nothing special just vulgar texts and graffiti's carved by some rascals with sharp objects.
This comments will appear every time player commits loop and re-enters room until they encounter [[Entity]] for the first time ...
Previously "Commentaries can change completely or small parts of them can be different" was mentioned . The reason for this is that there will some small changes in text and careful player can track [[Anomalies]] with that. In script some text places will be able to be formatted with game progression . For example the same message will appear on look command how ever the word "ETXI" will spelled in correct instead of correct "EXIT". this will point to anomaly that player need to consider . And in such way there will be different signals for anomalies for example in same messages instead of "i can see CCTV camera indicator blinking"  there will be "i can see CCTV camera indicator is on" kind of things. 