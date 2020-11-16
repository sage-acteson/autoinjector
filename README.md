# autoinjector

## TODO

- [ ] Components:
	- [x] Buzzer
		- [x] Setup a basic sketch, buzzing
		- [x] Decide on active vs. passive [passive for now]
		- [x] Decide on the best frequency it the buzzer is inside the case [maybe 1k, doesn't seem to matter]
	- [x] Potentiometer
		- [x] Set up a basic sketch, read the values
		- [x] Try reading in increases as a system interrupt
	- [x] Button
		- [x] Set up a basic sketch, digital read the input
		- [x] Try the input as a system interrupt
	- [x] Servo
		- [x] Set up a basic sketch, just get it to turn
		- [x] Set up a method to turn 90 degrees
	- [ ] Detecting rapid change
		- [ ] Decide on a structure for holding data
		- [ ] Calculate the averages every cycle? (10sec & 2sec?)
- [ ] Combine components:
	- [ ] If the fake heart rate is over a threshold set off the buzzer
	- [ ] If the buzzer is going off and the button is pressed cancel the injection
- [ ] Cleanup:
	- [ ] Replace the array logic with a LinkedList
- [ ] Housekeeping:
	- [ ] Add a description to this repo