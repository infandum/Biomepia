using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HexTileControler : MonoBehaviour
{
    public HexTile TileData = new HexTile();

    public HexTileControler(HexTile tileData)
    {
        TileData = tileData;
    }

    public void SetTile(HexTile tileData)
    {
        TileData = tileData;
    }
}
