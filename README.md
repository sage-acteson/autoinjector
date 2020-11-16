# autoinjector

## TODO

- [ ] Components:
	- [x] Buzzer
		- [x] Setup a basic sketch, buzzing
		- [x] Decide on active vs. passive [passive for now]
		- [x] Decide on the best frequency it the buzzer is inside the case [maybe 1k, doesn't seem to matter]
	- [ ] Rotary encoder
		- [x] Set up a basic sketch, ~~analog~~ read the values
		- [ ] Try reading in increases as a system interrupt
	- [ ] Button
		- [ ] Set up a basic sketch, digital read the input
		- [ ] Try the input as a system interrupt
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