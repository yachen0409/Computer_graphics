using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class startGame : MonoBehaviour
{
    public void StartGame(){
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex+1);
    }
    public void FromOne(){
        SceneManager.LoadScene(1);
    }
    public void FromTwo(){
        SceneManager.LoadScene(2);
    }
    public void FromThree(){
        SceneManager.LoadScene(3);
    }
}
