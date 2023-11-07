TextureCube cubeMap : register(t0);

SamplerState pointWrap : register(s0);
SamplerState pointClamp : register(s1);
SamplerState linearWrap : register(s2);

cbuffer cbPerObject : register(b0)
{
    float4x4 gWorld;
};

cbuffer cbPerPass : register(b1)
{
    float4x4 gViewProj;
    float3 gEyePos;
};

struct VertexIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float3 Normal : NORMAL;
    float2 TexCoord : TEXCOORD;
};

struct VertexOut
{
    float4 PosH : SV_Position;
    float3 PosL : POSITION;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
    
    vout.PosL = vin.Pos;

    float4 posW = mul(float4(vin.Pos, 1.0f), gWorld);

    posW.xyz += gEyePos;

    vout.PosH = mul(posW, gViewProj).xyww;
 
    return vout;
};

float4 PS(VertexOut pin) : SV_Target
{
    return cubeMap.Sample(linearWrap, pin.PosL);
};