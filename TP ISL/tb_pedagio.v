`timescale 1ns/1ps

// Testbench para módulo de pedágio
module tb_pedagio;
    
    // Entradas
    reg E1;
    reg E0;
    reg [3:0] P;
    
    // Saída do módulo testado
    wire [6:0] seg;

    reg [6:0] temp;

    // Instancia o módulo a ser testado
    pedagio uut (
        .E1(E1),
        .E0(E0), 
        .P(P),
        .seg(seg)
    );

    initial begin
        temp = 0;
        // Cria arquivo para análise de waveforms
        $dumpfile("pedagio.vcd");
        $dumpvars(0, tb_pedagio);

        // Valores iniciais
        E1 = 0; E0 = 0; P = 4'b0000;
    end

    // Testa todas as 64 combinações possíveis
    always @(*) begin
        while (temp < 64) begin
            // Distribui os bits de temp para as entradas
            E1 = temp[5];
            E0 = temp[4];
            P = temp[3:0];
            
            #5 // Aguarda 5ns
            
            // Mostra resultados
            $display("%4dns|%b%b|%b|%b|%d", $time, E1, E0, P, seg, temp);
            temp = temp + 1;         
        end
    end

endmodule