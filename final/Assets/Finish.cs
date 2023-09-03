using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;
public class Finish : MonoBehaviour
{
    // Start is called before the first frame update
    private static int currentgold;
    public int advancegold;
    public TMP_Text advancetext;
    public AudioSource levelsound;
    public AudioSource failsound;
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
        //curgold = currentgold;
    }
    private void OnTriggerEnter(Collider other){
        currentgold = FindObjectOfType<GameManager>().returngold();
        if(other.gameObject.tag == "Player"){
            if(currentgold >= advancegold){
            	levelsound.Play();
                SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex+1);
                currentgold = 0;
            }
            else{
                failsound.Play();
                advancetext.text = "Need " + (advancegold - currentgold) + " MORE Golds to Advance!";
                advancetext.color = Color.red;
            }
        }
    }
    public int returnadvancegold(){
        return advancegold;
    }
}
