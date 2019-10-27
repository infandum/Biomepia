using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;


[Serializable]
public class UV
{
    public float u;
    public float v;
    //public int width;
    //public int height;

    public UV()
    {
        this.u = 0.0f;
        this.v = 0.0f;
    }

    public UV(float u = 0.0f, float v = 0.0f)
    {
        this.u = u;
        this.v = v;
    }

    //public override bool Equals(object obj)
    //{
    //    return obj is UV uV &&
    //           u == uV.u &&
    //           v == uV.v;
    //}

    //protected bool Equals(UV other)
    //{
    //    return u.Equals(other.u) && v.Equals(other.v);
    //}

    //public override int GetHashCode()
    //{
    //    unchecked
    //    {
    //        return (u.GetHashCode() * 397) ^ v.GetHashCode();
    //    }
    //}
}

[Serializable]
public class HexTile
{
    public string Name = "HexTile";
    public Transform Transform;
    public Vector3 Position = new Vector3(0,0,0);
    public Vector3Int Index = new Vector3Int(0,0,0);
    public UV HeightUV = new UV(0, 0);
}