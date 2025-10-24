module pedagio (
    input  wire E1,
    input  wire E0,
    input  wire [3:0] P,
    output reg  [6:0] seg
);
    
    wire peso_le_12, peso_gt_12;
    wire C1, C2, C3, ERR;

    // Comparadores
    assign peso_gt_12 = P[3] & P[2] & (P[1] | P[0]);
    assign peso_le_12 = (~P[3]) | (~P[2]) | ((~P[1]) & (~P[0]));

    // Lógica das categorias
    assign C1 = (~P[3]) & (~E1) & (~E0);   // Carro
    assign C2 = peso_le_12 & (~E1) & E0;   // Caminhonete
    assign C3 = peso_gt_12 & E1;           // Caminhão
    assign ERR = ~(C1 | C2 | C3);          // Erro

    // Decodificador 7 segmentos (common cathode)
    always @(*) begin
        if (C1)      seg = 7'b0110000; // “1”
        else if (C2) seg = 7'b1101101; // “2”
        else if (C3) seg = 7'b1111001; // “3”
        else         seg = 7'b1001111; // “E”
    end
endmodule