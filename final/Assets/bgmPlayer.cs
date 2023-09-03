using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class bgmPlayer : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        int scenenum = SceneManager.GetActiveScene().buildIndex;
        if(scenenum > 3){
            Destroy(this.gameObject);
        }
    }
    public void Awake(){
    GameObject[] musics = GameObject.FindGameObjectsWithTag("music");
    if(musics.Length > 1){
        Destroy(this.gameObject);
    }
    DontDestroyOnLoad(this.gameObject);
    }
}
