import chess
import chess.pgn

#PGN a.k.a. "Portable Game Notation": https://en.wikipedia.org/wiki/Portable_Game_Notation

game = chess.pgn.Game()
game.headers["Event"] = "This is not a game..."
game.headers["Site"]  = "UAT"
game.headers["Date"]  = "may 23rd"
game.headers["Round"] = 1
game.headers["White"] = "da_poor_student"
game.headers["Black"] = "Rhino X-R3"

print("\n--------------------------------------------------------------")
print("\t\tExploring py-chess")
print("----------------------------------------------------------------\n")
print("Event: ",game.headers["Event"])
print("Site: ",game.headers["Site"])
print("Date: ",game.headers["Date"])
print("Round: ",game.headers["Round"])
print("White: ",game.headers["White"])
print("Black: ",game.headers["Black"])

print("\n\n")
