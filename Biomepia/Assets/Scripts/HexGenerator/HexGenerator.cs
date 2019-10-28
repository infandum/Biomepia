using System.Collections.Generic;
using Assets.Scripts.Helpers;
using UnityEngine;

namespace Assets.Scripts.HexGenerator
{
    public class HexGenerator : MonoBehaviour
    {
        [SerializeField] private GameObject _hexGameObject;
        public Vector2Int RectSize = new Vector2Int(10, 10);
        public int HexRadius = 14;

        public List<HexTile> HexTiles;

        public Texture2D HeightMap;
        [SerializeField] private Texture2D _heightIndexMap;
        public float HeightMultiplier = 1.0f;
        public float HeightGrowth = 1.0f;

        private readonly Vector3 _pivot = new Vector3(0.5f, 0.5f, 0.5f);
        private Bounds _bounds;

        private float _size = 1.0f;
        private float _tileXOffSet = 1.0f;
        private float _tileYOffSet = 0.0f;
        private float _tileZOffSet = 0.865f;

        public bool IsGenerateRect = true;
        public bool IsOnlyInsideCollider;
        private bool _isColliderRect;

        public void GenerateMap()
        {
            /* Clear all previous tiles */
            HexTiles = new List<HexTile>();
            while (transform.childCount > 0)
            {
                Helper.SafeDestroy(transform.GetChild(0).gameObject);
            }

            /* Check reference tile */
            if (!_hexGameObject)
                _hexGameObject = Resources.Load<GameObject>("Prefabs/Hex_1m");

            /* Check collider bounds */
            if (GetComponent<Collider>())
            {
                Collider colliderComponent = GetComponent<Collider>();
                _bounds = colliderComponent.bounds;

                /* Check collider is box */
                _isColliderRect = colliderComponent.GetType() == typeof(BoxCollider);

                if (_bounds.size.x <= 1 || _bounds.size.z <= 1)
                    IsOnlyInsideCollider = false;
            }
            else
                IsOnlyInsideCollider = false;


            /* Generate map */
            if (IsGenerateRect)
                CreateRectHexMap();
            else
                CreateHexagonalHexMap();

            /* Generate height */
            GenerateHeightFromTexture();
        }



        private void CreateRectHexMap()
        {
            /* Tile offset */
            _tileXOffSet = _size;
            _tileZOffSet = (Mathf.Sqrt(3) * _size);

            /* Map offset */
            var mapXOffset = RectSize.x * _pivot.x - 0.25f;
            var mapZOffset = RectSize.y * _pivot.z - 1.25f;

            for (int x = 0; x < RectSize.x; x++)
            {
                for (int z = 0; z < RectSize.y; z++)
                {
                    /* Offset position for uneven rows */
                    Vector3 pos = z % 2 == 0 ?
                        new Vector3(x * _tileXOffSet - mapXOffset, 0 * _tileYOffSet, z * (_tileZOffSet / 2) - mapZOffset) : 
                        new Vector3(x * _tileXOffSet + (_tileXOffSet / 2) - mapXOffset, 0 * _tileYOffSet, z * (_tileZOffSet / 2) - mapZOffset);

                    /* Generate tile */
                    GenerateHexagonTile(pos, x, z);                
                }
            }
        }

        private void CreateHexagonalHexMap()
        {
            InstantiateHexagonTile(new Vector3(), 0, 0);

            RectSize = new Vector2Int(HexRadius * 2, HexRadius * 2);

            _tileZOffSet = (Mathf.Sqrt(3) * _size);
            for (int x = 1; x <= HexRadius; x++)
            {
                /* place the hexagonal corner points */
                for (int index = 1; index <= 6; index++)
                {
                    /* Corner point angle from center */
                    int angle = (60 * index) + 30;
                    var pos = PositionAroundCircle(angle * (Mathf.PI / 180), x);

                    /* Grid index*/
                    int xIndex = pos.x > 0 ? x : -x;
                    int zindex = 0;

                    if (index != 1 && index != 4)
                        zindex = pos.z > 0 ? x : -x;

                    /* Generate tile */
                    GenerateHexagonTile(pos, xIndex, zindex);

                    /* place the hexagonal lines segments: number of segment pieces = radius[0,MAX] - 1*/
                    for (int i = 1; i < x; i++)
                    {
                        /* direction of the line segment: counter clock-wise */
                        var side = index + 1 % 6;
                        Vector3 linePos = HexCorners(pos, i, side, false);

                        /* Grid index*/
                        zindex = pos.z > 0 ? i : -i;

                        /* Generate tile */
                        GenerateHexagonTile(linePos, xIndex, zindex);
                    }
                }
            }
        }

        private void GenerateHexagonTile(Vector3 position, int xIndex, int zindex)
        {
            /* Round position to 0.001f */
            position = new Vector3(Mathf.Round(position.x * 1000.0f) / 1000.0f, Mathf.Round(position.y * 1000.0f) / 1000.0f, Mathf.Round(position.z * 1000.0f) / 1000.0f);

            if (IsOnlyInsideCollider)
            {
                /* use contain if bounding box is a rectangle */
                if (_isColliderRect)
                {
                    /* Is position inside the bounding collider */
                    if (_bounds.Contains(position))
                    {
                        InstantiateHexagonTile(position, xIndex, zindex);
                    }
                }
                /* Use the radius if bounding box is sphere */
                else
                {
                    /* Is position inside radius of the bounding collider */
                    float dist = Vector3.Distance(position, transform.position);
                    if (dist <= _bounds.size.x / 2)
                    {
                        InstantiateHexagonTile(position, xIndex, zindex);
                    }
                }
            }
            else
            {
                InstantiateHexagonTile(position, xIndex, zindex);
            }
        }

        private void InstantiateHexagonTile(Vector3 pos, int xIndex, int zindex)
        {
            var hex = Instantiate(_hexGameObject, transform);
            SetHexagonTile(hex, pos, xIndex, zindex);
        }

        private void SetHexagonTile(GameObject obj, Vector3 pos, float xIndex, float zIndex)
        {
            /* Return if object is null */
            if (!obj) return;

            obj.name = "Hex:" + Mathf.RoundToInt(xIndex).ToString() + "x" + Mathf.RoundToInt(zIndex).ToString();
            obj.transform.localPosition = pos;

            /* Set HexTileController component if object has none */
            if (!obj.GetComponent<HexTileController>())
                obj.AddComponent<HexTileController>();

            /* Set tile info */
            HexTile tile = new HexTile
            {
                Name = obj.name,
                Transform = obj.transform,
                Index = new Vector3Int((int)xIndex, 0, (int)zIndex)
            };

            Uv heightUv = new Uv
            {
                U = ((obj.transform.localPosition.x / (RectSize.x / 2.0f)) + 1) / 2,
                V = ((obj.transform.localPosition.z / (RectSize.y / 2.0f)) + 1) / 2
            };
            tile.HeightUv = heightUv;

            /* Add tile info to object controller */
            obj.GetComponent<HexTileController>().TileData = tile;

            /* Add tile array */
            HexTiles.Add(tile);
        }

        private void GenerateHeightFromTexture()
        {
            /* Return if no height map */
            if (HeightMap == null) return;

            /* Reference indexed height map for debugging */
            _heightIndexMap = new Texture2D(HeightMap.width, HeightMap.height);

            /* Copy base material Instantiation for debugging */
            var mat = new Material(transform.GetChild(0).GetComponent<MeshRenderer>().sharedMaterial);

            for (int i = 0; i < HexTiles.Count; i++)
            {
                /* Instantiate base material copy for debugging */
                Material newMat = Instantiate(mat);

                /* Get pixel position tile UV position */
                var posX = Mathf.RoundToInt(HexTiles[i].HeightUv.U * HeightMap.width);
                var posY = Mathf.RoundToInt(HexTiles[i].HeightUv.V * HeightMap.width);

                /* Get height from texture */
                var elevation = GetHeightFromTexture(posX, posY);

                /* Height growth: exponential height modifier*/
                elevation = Mathf.Pow(elevation, HeightGrowth);

                /* Height Max: linear maximum height*/
                elevation = Mathf.Lerp(0.0f, HeightMultiplier, elevation);

                /* Set material copy Instance info*/
                Color col = new Color(elevation, elevation, elevation);
                newMat.name = col.grayscale.ToString("F");
                newMat.SetColor("_BaseColor", col);

                /* Set HexTile*/
                HexTiles[i].Transform.GetComponent<MeshRenderer>().sharedMaterial = newMat;
                HexTiles[i].Transform.position = new Vector3(transform.GetChild(i).position.x, elevation, transform.GetChild(i).position.z);
            }
        }
        public static Vector3 HexCorners(Vector3 center, float size, int sideIndex, bool isPointyHex = true)
        {
            float angleDeg = 60 * sideIndex + ((isPointyHex == false) ? 0 :  30);
            float angleRad = Mathf.PI / 180 * angleDeg;

            float x = center.x + size * Mathf.Cos(angleRad);
            float y = 0;
            float z = center.z + size * Mathf.Sin(angleRad);

            return new Vector3(x, y, z);
        }
   
        public static Vector3 PositionAroundCircle(float rad, float radius)
        {
            float x = radius * Mathf.Sin(rad);
            float y = 0;
            float z = radius * Mathf.Cos(rad);
            return new Vector3(x, y, -z);
        }

        private float GetHeightFromTexture(int x, int y)
        {
            /* No height map, returns -1 height */
            if (!HeightMap) return -1;

            /* Size of the tile too pixel ratio for texture sampling */
            int sampleSize = HeightMap.width / RectSize.x;

            /* Get the average color from map  */
            Color col = GetAverageRgbCircle(HeightMap, x, y, sampleSize);

            /* Save the average color too map for debugging */
            SetAverageRgbCircle(_heightIndexMap, x, y, sampleSize, col);

            /* return float greyscale */
            return col.grayscale;
        }

        public void SetAverageRgbCircle(Texture2D img, int x, int y, int radius, Color color)
        {
            /* Iterate through a bounding box in which the circle lies */
            for (int i = x - radius; i < x + radius; i++)
            {
                for (int j = y - radius; j < y + radius; j++)
                {
                    /* If the pixel is outside the canvas, skip it */
                    if (i < 0 || i >= img.width || j < 0 || j >= img.height)
                        continue;

                    /* If the pixel is outside the circle, skip it */
                    if (Vector2.Distance(new Vector2(x, y), new Vector2(i, j)) > radius)
                        continue;

                    /* Set the color too the image */
                    img.SetPixel(Mathf.RoundToInt(i), Mathf.RoundToInt(j), color);

                }
            }
            /* Apply texture changes */
            img.Apply();
        }

        public Color GetAverageRgbCircle(Texture2D img, int x, int y, int radius)
        {
            float r = 0;
            float g = 0;
            float b = 0;
            int num = 0;
            /* Iterate through a bounding box in which the circle lies */
            for (int i = x - radius; i < x + radius; i++)
            {
                for (int j = y - radius; j < y + radius; j++)
                {
                    /* If the pixel is outside the canvas, skip it */
                    if (i < 0 || i >= img.width || j < 0 || j >= img.height)
                        continue;

                    /* If the pixel is outside the circle, skip it */
                    if(Vector2.Distance(new Vector2(x , y), new Vector2(i, j)) > radius)
                        continue;


                    /* Get the color from the image, add to a running sum */
                    Color c = img.GetPixel(i, j);
                    /* Sum the squares of components instead */
                    r += c.r * c.r;
                    g += c.g * c.g;
                    b += c.b * c.b;
                    num++;
                }
            }
            /* Return the sqrt of the mean of squared R, G, and B sums */
            return new Color(Mathf.Sqrt(r / num), Mathf.Sqrt(g / num), Mathf.Sqrt(b / num));
        }

    }
}
