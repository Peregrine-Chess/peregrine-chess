<div align="center">
    <img src="./assets/cheese_smol.png" style="max-width:15vw;"><br>
    <img src="https://img.shields.io/github/commit-activity/w/cheese-chess/cheese_c?style=flat-square">
    <img src="https://img.shields.io/github/license/cheese-chess/cheese_c?style=flat-square">
    <img src="https://img.shields.io/discord/872146521183903804?style=flat-square">
    <h1>Cheese Chess Engine (CCE)</h1>

</div>

A UCI (not yet) chess engine written in C.

## Dependancies
```
make
```

## Roadmap
This is a short-term roadmap, because I don't know how to make long term ones

- [x] Implement bitboards
- [x] Implement bit counter
- [x] Generate piece attack bitboards
- [x] Generate occupancy bitboards
- [x] Generate magic numbers for magic bitboards
- [ ] (In progress) Initialize slider piece attacks using plain magic bitboards
- [ ] Generate legal moves for each piece
- [ ] Negamax Search
- [ ] Quiescence Search

## Running
It still doesn't even do anything, why would you want to run it??? Anyway:
```bash
# Clone this repo
git clone https://github.com/cheese-chess/cheese_c
# Go into the repo (duh, if you didn't know that, you shouldn't be compiling software)
cd cheese_c
# Run make to compile
make
# Then run it
make run
# If you want to install it, even if it doesnt do anything, run this as root (using sudo or doas or something, we really don't care):
make install
```

## Credits
- [@aa2006](https://github.com/aa2006) for code.
- [@segfaultdev](https://github.com/segfaultdev) for idk what.
- [@DamieFC](https://github.com/DamieFC) for adding extra to the duh
