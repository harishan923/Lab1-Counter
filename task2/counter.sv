module counter #(
    parameter WIDTH = 8
)(
    //interface signals
    input  logic             clk, //clock
    input  logic             rst,
    input  logic             en,
    output logic [WIDTH-1:0] count
);

// Synchronous Reset

/*
always_ff @ (posedge clk)
    if (rst) count <= {WIDTH{1'b0}};
    else count <= count + {{WIDTH-1{1'b0}}, en};
*/

// Asynchronous Reset

always_ff @ (posedge clk, posedge rst)
    if (rst) count <= {WIDTH{1'b0}};
    else count <= count + {{WIDTH-1{1'b0}}, en};

endmodule

