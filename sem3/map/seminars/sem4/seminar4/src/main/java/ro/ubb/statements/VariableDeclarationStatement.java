package ro.ubb.statements;

import ro.ubb.state.ProgramState;
import ro.ubb.type.IType;


public record VariableDeclarationStatement(
            IType type, String variableName ) implements  IStatement{

    @Override
    public void execute(ProgramState programState){
        // TODO
    }
}
