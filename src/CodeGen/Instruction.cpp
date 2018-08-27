#include "CodeGen/Instruction.h"

namespace elma {

bool Instruction::isBinaryOp() const
{
    switch (opcode) {
    case Opcode::Add:
    case Opcode::Sub:
    case Opcode::Mul:
    case Opcode::Div:
    case Opcode::CompareEqual:
    case Opcode::CompareNotEqual:
    case Opcode::CompareGreaterThan:
    case Opcode::CompareGreaterThanOrEqual:
    case Opcode::CompareLessThan:
    case Opcode::CompareLessThanOrEqual: return true; break;
    default: break;
    }
    return false;
}

} // namespace elma
