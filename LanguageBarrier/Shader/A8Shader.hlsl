Texture2D<float4> Texture : register(t0);
sampler TextureSampler : register(s0);

float4 MySpritePixelShader(float4 color : COLOR0,
    float2 texCoord : TEXCOORD0) : SV_Target0
{
    float alpha = Texture.Sample(TextureSampler, texCoord).a;
    return float4(color.xyz, alpha);
}