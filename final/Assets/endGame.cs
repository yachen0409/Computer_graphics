using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class endGame : MonoBehaviour
{
    void Start()
    {

    }
    public void toMainmenu(){
        SceneManager.LoadScene(0);
    }
    public void EndGame(){
        Application.Quit();
    }
}
