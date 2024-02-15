// Concepts for Stochastic Processes
//
// Interface requirements on physical processes supported
// in our stochastic differential equations.
//
// Variables used herein:
// Process p: e.g. GBM, Jump-Diffusion, Heston, etc.
// Data t: time
// Data x: space / price
//
// Tobias Bilgeri, 15.02.2024

// Diffusion:
template<typename Process, typename Data>
concept IDiffusion = requires (Process p, Data t, Data x)
{
	p.diffusion(t, x);
};

// Drift
template<typename Process, typename Data>
concept IDrift = requires (Process p, Data t, Data x)
{
	p.drift(t, x);
};

// Jump
template<typename Process, typename Data>
concept IJump = requires (Process p, Data t, Data x)
{
	p.jump(t, x);
};

// Drift + Diffusion (such as in black-scholes)
template<typename Process, typename Data>
concept IDriftDiffusion = 
	IDrift<Process, Data> &&
	IDiffusion<Process, Data>;

// Drift + Jump + Diffusion
template<typename Process, typename Data>
concept IDriftJumpDiffusion =
	IDrift<Process, Data> &&
	IJump<Process, Data>&&
	IDiffusion<Process, Data>;
