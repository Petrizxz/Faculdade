`timescale 1ns/1ps
module tb_pedagio;
    // Entradas (reg porque vamos alterar no tempo)
    reg E1;
    reg E0;
    reg [3:0] P;
    // Saída (wire porque vem do módulo)
    wire [6:0] seg;

    reg [6:0] temp;

    // Instancia o módulo a ser testado
    // Liga as entradas no modulo do verilog.v
    pedagio uut (
        .E1(E1),
        .E0(E0),
        .P(P),
        .seg(seg)
    );

    // Bloco inicial de simulação
    initial begin
        temp = 0;
        $dumpfile("pedagio.vcd");
        $dumpvars(0, tb_pedagio);   

        // Define valores iniciais
        E1 = 0; E0 = 0; P = 4'b0000;

    end

    always @(*) begin
        while (temp<64) begin
            E1 = temp[5];
            E0 = temp[4];
            P = temp[3:0];
            #5
            $display("%4dns|%b%b|%b|%b|%d",$time,E1,E0,P,seg,temp);
            temp = temp + 1;         
        end
    end

endmodule
