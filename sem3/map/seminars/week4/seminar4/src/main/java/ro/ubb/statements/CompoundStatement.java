package ro.ubb.statements;

import ro.ubb.state.ProgramState;

public record CompoundStatement(iStatement first, iStatement second) implements iStatement {
    @Override
    public void execute(ProgramState programState) {
    }
}
