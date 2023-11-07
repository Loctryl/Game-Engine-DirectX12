Texture2D tex : register(t0);

SamplerState pointWarp : register(s0);

cbuffer cbPerObject : register(b0)
{
    float4x4 gWorld;
    float4 gColor;
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
    float4 PosH : SV_POSITION;
    float3 PosW : POSITION;
    float3 NormalW : NORMAL;
    float4 Color : COLOR;
};

VertexOut VS(VertexIn vin)
{
    VertexOut vout;
    
    // Transform to world space.
    float4 posW = mul(float4(vin.Pos, 1.0f), gWorld);
    vout.PosW = posW.xyz;
    
    vout.NormalW = mul(vin.Normal, (float3x3) gWorld);
    //vout.NormalW = vin.Normal;
    
    // Transform to homogeneous clip space.
    vout.PosH = mul(posW, gViewProj);
    
    // Just pass vertex color into the pixel shader.
    vout.Color = gColor;
    return vout;
};

float4 PS(VertexOut pin) : SV_Target
{
    // Interpolating normal can unnormalize it, so renormalize it.
    float3 N = normalize(pin.NormalW);
    float3 L = normalize(gLightDir);
  
    //const float shineness = 1.0f - gRoughness;
    
    // dot product entre normal et dirLight
    float dotProd = clamp(dot(N, L), 0.05, 0.95);

    float4 litcolor = pin.Color + (dotProd * (gLightColor));
   
    litcolor.a = gDiffuseAlbedo.a;
    
    return litcolor;
};