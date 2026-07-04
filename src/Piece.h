#pragma once
#include <string>
enum class PieceType { None, Pawn, Rook, Knight, Bishop, Queen, King };
enum class PieceColor { White, Black };


struct Piece {
    PieceType type;
    PieceColor color;
    bool operator==(const Piece& other) const {
        return type == other.type && color == other.color;
    }

    std::string toString() const {
        if (type == PieceType::None) return "None";
        std::string name;
        switch (type) {
            case PieceType::Pawn:   name = "Pawn";   break;
            case PieceType::Rook:   name = "Rook";   break;
            case PieceType::Knight: name = "Knight"; break;
            case PieceType::Bishop: name = "Bishop"; break;
            case PieceType::Queen:  name = "Queen";  break;
            case PieceType::King:   name = "King";   break;
            default:                name = "?";      break;
        }
        return (color == PieceColor::White ? "W" : "B") + name;
    }
};
